#include <stdio.h>
#include "sgx_urts.h"
#include "enclave_u.h"

#define max_data_size 20

int ocall_test(char *data, size_t data_len){
  printf("cmd 0: %s\n", data);

  return 0;
}

int main(void){
  sgx_enclave_id_t eid;
  //sgx_status_t res=SGX_SUCCESS;
  sgx_status_t res;
  sgx_launch_token_t token={0};
  char *enclave_name="enclave.signed.so";
  int updated=0;
  int retval;

  //create enclave
  res=sgx_create_enclave(enclave_name, SGX_DEBUG_FLAG, &token, &updated,
			 &eid, NULL);
  if(res!=SGX_SUCCESS){
    printf("error %#x, failed to create enclave\n", res);
    return -1;
  }

  //ecall
  int cmd=0;
  char *data;
  res=ecall_test(eid, &retval, &cmd, sizeof(cmd), data, max_data_size);
  if(res!=SGX_SUCCESS){
    printf("error %#x, failed to do ecall_test\n", res);
    return -1;
  }
  
  cmd=1;
  res=ecall_test(eid, &retval, &cmd, sizeof(cmd), data, max_data_size);
  if(res!=SGX_SUCCESS){
    printf("error %#x, failed to do ecall_test\n", res);
    return -1;
  }
  printf("cmd 1: %s\n", data);

  //destroy enclave
  sgx_destroy_enclave(eid);

  return 0;
}
