#include <jni.h>
#include <string>

#include <unistd.h>
#include <sys/mman.h>

#include "log.h"

char * memory= nullptr;

extern "C" JNIEXPORT jstring JNICALL
Java_com_shocker_mincore_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "点击测试";
    memory= (char*)mmap(nullptr,0x4000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_shocker_mincore_MainActivity_mincore(JNIEnv *env, jobject thiz) {
    // TODO: implement mincore()
    int pageSize = getpagesize();
    unsigned char vec = 0;
//    memory[0]=1;
    unsigned long addr= reinterpret_cast<unsigned long>(memory);
    unsigned long start = addr & (~(pageSize - 1));
    mincore((void *)start, pageSize, &vec);
    if (vec == 1)
    {
        LOGD("内存页：%p 存在于物理内存空间",addr);
    }else{
        LOGD("内存页：%p 不存在于物理内存空间",addr);
    }
}