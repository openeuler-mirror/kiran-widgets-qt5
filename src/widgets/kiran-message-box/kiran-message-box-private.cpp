#include "kiran-message-box-private.h"
#include "kiran-message-box.h"
#include "xlib-helper.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QMetaEnum>
#include <QMouseEvent>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

///默认按钮信息Map QMap<默认按钮枚举值,<按钮文本,按钮角色>>
static const QMap<KiranStandardButton,QPair<QString,ButtonRole>> standardButtonInfoMap = {
    {KiranMessageBox::Ok,{QObject::tr("OK"),ButtonRole::AcceptRole}},
    {KiranMessageBox::Save,{QObject::tr("Save"),ButtonRole::AcceptRole}},
    {KiranMessageBox::SaveAll,{QObject::tr("Save All"),ButtonRole::AcceptRole}},
    {KiranMessageBox::Open,{QObject::tr("Open"),ButtonRole::AcceptRole}},
    {KiranMessageBox::Yes,{QObject::tr("Yes"),ButtonRole::YesRole}},
    {KiranMessageBox::YesToAll,{QObject::tr("Yes to All"),ButtonRole::YesRole}},
    {KiranMessageBox::No,{QObject::tr("No"),ButtonRole::NoRole}},
    {KiranMessageBox::NoToAll,{QObject::tr("No to All"),ButtonRole::NoRole}},
    {KiranMessageBox::Abort,{QObject::tr("Abort"),ButtonRole::RejectRole}},
    {KiranMessageBox::Retry,{QObject::tr("Retry"),ButtonRole::AcceptRole}},
    {KiranMessageBox::Ignore,{QObject::tr("Ignore"),ButtonRole::AcceptRole}},
    {KiranMessageBox::Close,{QObject::tr("Close"),ButtonRole::RejectRole}},
    {KiranMessageBox::Cancel,{QObject::tr("Cancel"),ButtonRole::RejectRole}},
    {KiranMessageBox::Discard,{QObject::tr("Discard"),ButtonRole::DestructiveRole}},
    {KiranMessageBox::Help,{QObject::tr("Help"),ButtonRole::HelpRole}},
    {KiranMessageBox::Apply,{QObject::tr("Apply"),ButtonRole::ApplyRole}},
    {KiranMessageBox::Reset,{QObject::tr("Reset"),ButtonRole::ResetRole}},
    {KiranMessageBox::RestoreDefaults,{QObject::tr("Restore Defaults"),ButtonRole::ResetRole}}
};

static const QColor inactivatedColor("#222222");
static const int    inactivatedBlurRadius = 10;

static const QColor activatedColor("#000000");
static const int    activatedBlurRadius = 18;

KiranMessageBoxPrivate::KiranMessageBoxPrivate(KiranMessageBox *ptr)
    : q_ptr(ptr),
      m_layout(nullptr),
      m_frame(nullptr),
      m_frameLayout(nullptr),
      m_titleWidget(nullptr),
      m_titleLayout(nullptr),
      m_iconLabel(nullptr),
      m_titleLabel(nullptr),
      m_textLabel(nullptr),
      m_standardButtons(KiranMessageBox::NoButton),
      m_dialogButtonBox(nullptr),
      m_dropShadowEffect(nullptr),
      m_titlebarIsPressed(false),
      m_clickedStandardButton(KiranMessageBox::NoButton)
{
    m_dropShadowEffect = new QGraphicsDropShadowEffect(q_ptr);
    m_dropShadowEffect->setOffset(0,0);
    m_dropShadowEffect->setEnabled(false);
    q_func()->setGraphicsEffect(m_dropShadowEffect);
}

void KiranMessageBoxPrivate::init(const QString &title,
                                  const QString &text)
{
    ///加载样式表
    QFile file(":/kiranwidgets-qt5/themes/kiran-messagebox_black.qss");
    if( file.open(QIODevice::ReadOnly) ){
        QString styleSheet = file.readAll();
        q_func()->setStyleSheet(styleSheet);
    }

    m_layout = new QVBoxLayout(q_ptr);
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_frame = new QFrame(q_ptr);
    m_frame->setObjectName("KiranMessageBoxFrame");
    m_layout->addWidget(m_frame);

    m_frameLayout = new QVBoxLayout(m_frame);
    m_frameLayout->setSpacing(5);
    m_frameLayout->setContentsMargins(24,0,24,24);

    ///标题栏
    m_titleWidget = new QWidget(q_ptr);
    m_titleWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_titleWidget->setFixedHeight(40);
    m_frameLayout->addWidget(m_titleWidget);

    m_titleLayout = new QHBoxLayout(m_titleWidget);
    m_titleLayout->setSpacing(2);
    m_titleLayout->setMargin(0);

    m_iconLabel = new QLabel(m_titleWidget);
    m_iconLabel->setFixedSize(QSize(16,16));
    m_iconLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_titleLayout->addWidget(m_iconLabel);

    m_titleLabel = new QLabel(m_titleWidget);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    m_titleLabel->setText(title);
    QFont font = m_titleLabel->font();
    font.setPixelSize(16);
    m_titleLabel->setFont(font);
    m_titleLayout->addWidget(m_titleLabel);

    QLabel *spacingLabel = new QLabel(m_titleLabel);
    spacingLabel->setFixedSize(QSize(16,16));
    spacingLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_titleLayout->addWidget(spacingLabel);

    ///正文
    m_textLabel = new QLabel(m_frame);
    m_textLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_textLabel->setWordWrap(true);
    m_textLabel->setScaledContents(false);
    m_textLabel->setText(text);
    m_textLabel->setMaximumWidth(qApp->desktop()->width()/4);
    m_textLabel->setMaximumHeight(qApp->desktop()->height()/4);
    m_frameLayout->addWidget(m_textLabel);

    QSpacerItem* spacerItem_1 = new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Expanding);
    m_frameLayout->addItem(spacerItem_1);

    ///按钮盒
    m_dialogButtonBox = new QDialogButtonBox(Qt::Horizontal,m_frame);
    m_dialogButtonBox->setCenterButtons(true);
    m_dialogButtonBox->setFixedHeight(40);
    m_dialogButtonBox->layout()->setSpacing(58);
    m_frameLayout->addWidget(m_dialogButtonBox);

    q_ptr->setMinimumSize(300,180);
}

void KiranMessageBoxPrivate::setIcon(const QString &iconPath)
{
    QIcon icon(iconPath);
    if( icon.isNull() ){
        return;
    }
    m_iconLabel->setPixmap(iconPath);
}

void KiranMessageBoxPrivate::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void KiranMessageBoxPrivate::setText(const QString &text)
{
    m_textLabel->setText(text);
}

QPushButton *KiranMessageBoxPrivate::addButton(KiranStandardButton standardButton)
{
    ///是否已经添加过该默认按钮
    auto iter = m_standardButtonsMap.find(standardButton);
    if( iter!=m_standardButtonsMap.end() ){
        return iter.value();
    }

    ///判断按钮类型正确
    auto buttonInfoIter = standardButtonInfoMap.find(standardButton);
    if( buttonInfoIter==standardButtonInfoMap.end() ){
        qWarning() << "wrong standard button type," << standardButton;
        return nullptr;
    }

    QPushButton *button = new QPushButton(q_ptr);
    button->setFixedSize(QSize(100,40));
    button->setText(buttonInfoIter.value().first);

    ///生成ObjectName，eg:KiranStandardButton::Ok->btn_Ok
    QMetaEnum metaEnum = QMetaEnum::fromType<KiranStandardButton>();
    QString standardButtonString = metaEnum.valueToKey(standardButton);
    standardButtonString.replace(" ","_");
    QString objectName = QString("btn_%1").arg(standardButtonString);
    button->setObjectName(objectName);

    m_standardButtons |= standardButton;
    m_standardButtonsMap.insert(standardButton,button);
    m_dialogButtonBox->addButton(button,buttonInfoIter.value().second);
    return button;
}

QPushButton *KiranMessageBoxPrivate::addButton(const QString &text,
                                               QDialogButtonBox::ButtonRole role)
{
    QPushButton *button = new QPushButton(m_dialogButtonBox);
    button->setFixedSize(100,40);
    button->setText(text);
    m_dialogButtonBox->addButton(button,role);
    return button;
}

void KiranMessageBoxPrivate::removeButton(QPushButton *button)
{
    m_dialogButtonBox->removeButton(button);
}

void KiranMessageBoxPrivate::setStandarButtons(KiranStandardButtons standardButtons)
{
    for(auto iter=m_standardButtonsMap.begin();
        iter!=m_standardButtonsMap.end();
        iter++){
        QPushButton* button = iter.value();
        m_dialogButtonBox->removeButton(button);
        delete button;
    }

    m_standardButtons = KiranMessageBox::NoButton;
    m_standardButtonsMap.clear();

    QMetaEnum metaEnum = QMetaEnum::fromType<KiranStandardButton>();
    for(int i=0;i<metaEnum.keyCount();i++){
        if( standardButtons & metaEnum.value(i) ){
            addButton(static_cast<KiranStandardButton>(metaEnum.value(i)));
        }
    }
}

KiranStandardButton KiranMessageBoxPrivate::standardButton(QAbstractButton *button)
{
    KiranStandardButton findButton = KiranStandardButton::NoButton;
    for(auto iter = m_standardButtonsMap.begin();
        iter != m_standardButtonsMap.end();
        iter++){
        if( iter.value() == button ){
            findButton = iter.key();
            break;
        }
    }
    return findButton;
}

QPushButton *KiranMessageBoxPrivate::button(KiranStandardButton which)
{
    auto iter = m_standardButtonsMap.find(which);
    if(iter==m_standardButtonsMap.end()){
        return nullptr;
    }
    return iter.value();
}

void KiranMessageBoxPrivate::enableShadow(bool enable)
{
    m_dropShadowEffect->setEnabled(enable);
    m_layout->setMargin(enable?SHADOW_BORDER_WIDTH:0);
    ///NOTE:获取缩放率x(阴影边框宽度+窗口边框)
    int shadowBorderWidth = (SHADOW_BORDER_WIDTH+1)*q_ptr->devicePixelRatio();
    XLibHelper::SetShadowWidth(QX11Info::display(),
                               q_ptr->winId(),
                               enable?shadowBorderWidth:0,
                               enable?shadowBorderWidth:0,
                               enable?shadowBorderWidth:0,
                               enable?shadowBorderWidth:0);
}

void KiranMessageBoxPrivate::handleMouseButtonPressEvent(QMouseEvent *event)
{
    if( event->button()!=Qt::LeftButton ){
        return;
    }

    if( m_titleWidget->frameGeometry().contains(event->pos()) ){
        m_titlebarIsPressed = true;
    }
}

void KiranMessageBoxPrivate::handleMouseButtonReleaseEvent(QMouseEvent *event)
{
    if(  event->button() == Qt::LeftButton ){
        if(m_titlebarIsPressed){
            m_titlebarIsPressed = false;
        }
    }
}

void KiranMessageBoxPrivate::handlerMouseMoveEvent(QMouseEvent *event)
{
    if( m_titlebarIsPressed ){
        QPoint pos = QCursor::pos();
        pos *= q_func()->devicePixelRatio();
        XLibHelper::sendWMMoveEvent(QX11Info::display(),
                                    q_func()->winId(),
                                    pos.x(),
                                    pos.y());
        ///NOTE:在此之后获取不到MouseRelease事件,需复位按钮按压
        m_titlebarIsPressed = false;
        event->accept();
        return;
    }
}

void KiranMessageBoxPrivate::handlerActivationChangeEvent(bool active)
{
    bool showShadow = ( QX11Info::isCompositingManagerRunning() && (!(q_func()->windowState()&Qt::WindowFullScreen)));
    if( Q_LIKELY(m_dropShadowEffect && showShadow) ){
        m_dropShadowEffect->setColor(active?activatedColor:inactivatedColor);
        m_dropShadowEffect->setBlurRadius(active?activatedBlurRadius:inactivatedBlurRadius);
    }
}

void KiranMessageBoxPrivate::setButtonSize(const QSize &size) {
    if( m_buttonSize==size ){
        return;
    }
    QList<QAbstractButton*> btns = m_dialogButtonBox->buttons();
    for( QAbstractButton*btn : btns ){
        btn->setFixedSize(size);
    }
    m_buttonSize = size;
}

void KiranMessageBoxPrivate::addButton(QPushButton *button, QDialogButtonBox::ButtonRole role) {
    m_dialogButtonBox->addButton(button,role);
}

void KiranMessageBoxPrivate::cleanButton() {
    m_dialogButtonBox->clear();
}
