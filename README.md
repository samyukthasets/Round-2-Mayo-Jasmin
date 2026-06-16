# Round-2-Mayo-Jasmin
Bitsliced Jasmin Implementation of Mayo signature scheme, compiled with **Jasmin Compiler 2025.06.3**


# Compiling and Executing

NIST api is available in the **test_NIST_signverif.c** file.
To compile the code, run:

```bash
make sign
./sign

```

# Benchmarking of Mayo2 implementation

Benchmarked based on the average of 100 runs of the implementation on a **5.2GHz x86_64 processor** with **16 GB RAM**.

| Scheme   | Public Key Size | Signature Size |
|----------|-----------------|----------------|
| Mayo 2   | 4912 bytes      | 186 bytes      |

| Primitive | Bitsliced Jasmin Implementation | Nibble-sliced 'C' Reference Implementation |
|-----------|---------------------------------|--------------------------------------------|
| Keygen    | 10.55 msecs                     | 4.06 msecs                                 |
| Sign      | 8.21 msecs                      | 3.07 msecs                                 |
| Verify    | 0.17 msecs                      | 1.66 msecs                                 |



