RPC Code Generator



A C++17 RPC code generator that parses a simplified Protocol Buffers definition and generates C/C++ message and service client code.



The project also includes a TLS runtime based on mbedTLS and an automated GitHub Actions CI pipeline.



Features



\- Parse `.proto` files

\- Generate C message structures

\- Generate serialization/deserialization functions

\- Generate RPC service client interfaces

\- RPC client runtime

\- TLS communication using mbedTLS

\- Certificate verification

\- TLS handshake testing

\- CMake build system

\- Automated GitHub Actions CI



\## Architecture



```text

.proto file

 |

 v

ProtoParser

 |

 +---- Message definitions

 |

 +---- Service definitions

 |

 v

CodeGenerator

 |

 +---- Message .h/.c files

 |

  +---- Service .h/.cpp files

  |

  v

Generated RPC Client

  |

  v

RpcClient

  |

  v

TlsClient

  |

  v

TLS / Network

