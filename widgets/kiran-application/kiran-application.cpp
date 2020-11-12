//
// Created by lxh on 2020/11/10.
//

#include "kiran-application.h"
#include "kiran-application-private.h"

KiranApplication::KiranApplication(int &argc, char **argv, int appFlags)
    : QApplication(argc,argv,appFlags),d_ptr(new KiranApplicationPrivate(this)){
    d_ptr->init();
};

KiranApplication::~KiranApplication(){
    delete d_ptr;
}