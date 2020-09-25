#include "enclave_t.h"
#include <string.h>

int ecall_test(int *cmd, size_t cmd_len, char *data, size_t data_len){
  char *message="hello sgx";
  int retval;
  
  if(*cmd==0){
    data=NULL;
    ocall_test(&retval, message, sizeof(message)+1);
  }else{
    if(*cmd==1){
      memcpy(data, message, strlen(message)+1);
    }
  }

  return 0;
}
    
