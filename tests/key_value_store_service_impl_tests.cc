#include <gtest/gtest.h>

#include "../cpp/key_value_store_service_impl.h"
#include "../cpp/backendStore.grpc.pb.h"
#include "../cpp/backendStore.pb.h"

// adds two values to the KeyValueStore under the same key
TEST(PutTest, SameKeyTest){
  KeyValueStore test_store;
  test_store.put("1testkey", "1testvalue");
  test_store.put("1testkey", "2testvalue");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
