SGX実行

最初にあるべきもの
enclave.edl : 関数の定義が書かれている
app.c、enclave.c : 敷居を超える関数の呼び出しは多分変わるから仮状態
enclave_config.xml : enclaveの情報を記したもの
key.pem : 秘密鍵

App.cを作成
↓
enclave.edlを作成
/opt/intel/sgxsdk/bin/x64/sgx_edger8r enclave.edl (x64とかはマシンで変わる)
↓
色々生成される
↓
enclave_u.h・enclave_t.hをみてシグネチャが変更されているのを確認して関数の定義と呼び出しを書く
ただし、呼び出し関数はシグネチャに注意
↓
enclave.cとenclave_t.cをコンパイルしてオブジェクトファイルに
↓
上記の二つをリンクさせる(共有オブジェクト)
gcc enclave_t.o enclave.o -o enclave.so -L/opt/intel/sgxsdk/lib64 -Wl,--whole-archive -lsgx_trts -Wl,--no-whole-archive -Wl,--start-group -lsgx_tstdc -lsgx_tcxx -lsgx_tcrypto -lsgx_tservice -Wl,--end-group -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined -Wl,-pie,-eenclave_entry -Wl,--export-dynamic -Wl,--defsym,__ImageBase=0 -nostdlib
↓
sgx_signツールを用いて用意した秘密鍵で署名
/opt/intel/sgxsdk/bin/x64/sgx_sign sign -key key.pem -enclave enclave.so -out enclave.signed.so -config enclave_config.xml
↓
app.cとenclave_u.cをリンクしてコンパイル
gcc app.c enclave_u.c -o app -I /opt/intel/sgxsdk/include -L/opt/intel/sgxsdk/lib64 -lsgx_urts
↓
実行