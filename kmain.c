struct example {
  unsigned char   config;
  unsigned short  address;
  unsigned char   index;
} __attribute__((packed));

int kmain() {
  return 0xdeadface;
}
