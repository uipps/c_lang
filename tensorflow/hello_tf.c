/*

cd /Users/cf/develope/c/c_lang_dev/tensorflow/
gcc hello_tf.c -ltensorflow -o hello_tf

*/
#include <stdio.h>
#include <tensorflow/c/c_api.h>

int main() {
  printf("Hello from TensorFlow C library version %s\n", TF_Version());
  return 0;
}
