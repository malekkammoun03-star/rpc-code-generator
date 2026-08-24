\# RPC Code Generator



A C++17 RPC code generator that parses a simplified Protocol Buffers definition and generates C/C++ message and service client code.



The project also includes a TLS runtime based on mbedTLS and an automated GitHub Actions CI pipeline.



\## Features



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

&#x20;   |

&#x20;   v

ProtoParser

&#x20;   |

&#x20;   +---- Message definitions

&#x20;   |

&#x20;   +---- Service definitions

&#x20;   |

&#x20;   v

CodeGenerator

&#x20;   |

&#x20;   +---- Message .h/.c files

&#x20;   |

&#x20;   +---- Service .h/.cpp files

&#x20;   |

&#x20;   v

Generated RPC Client

&#x20;   |

&#x20;   v

RpcClient

&#x20;   |

&#x20;   v

TlsClient

&#x20;   |

&#x20;   v

TLS / Network

