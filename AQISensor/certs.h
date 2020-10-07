#ifndef CERTS_H
#define CERTS_H

// Amazon's root CA. This should be the same for everyone
const char AWS_CERT_CA[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";

// The private key for your device
const char AWS_CERT_PRIVATE[] = "-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEAwpTXP5ecZ4/9ybPTwSX+09IoNlRgksoLaHRxgtT/0yW1cPXO\n" \
"8fqBlnZYTagl2W6ibUk3dIxvIWsBYj+4q7KM3YZe9e0yAfI5jQoSeCgd2+70u2eU\n" \
"VRpCf6vgpz4lPy7ogSKPBcLzQDDdQ1pDcxNClz5eo3U/WYW0z72NVpg9pSUKJb4N\n" \
"V0jjHEqhiDoWUDNs2eYpybNPPjU71RbIWtN80TVKqU7ot78HMcyz7vSQiUQCNMAX\n" \
"w9jvlN0YXNDVkhaeatrE8fz6DZ06Zx0s/rxirHSk4Y2+YabumEZxOuGQV3R8w/eU\n" \
"rfCEjs9rYYCYuTqof2eo7KsgIfF3pPiv/e6vuQIDAQABAoIBAEsvTdihkWqmxa5p\n" \
"ULoCH2vjeWw8wDAX576Nt8qQ2OTSXkBuim8Pl4D263neLfnM+O/3aXkcRliISzmW\n" \
"W5nkXO+/2vN1mmwMF1a6/JX3EkqIE4JSLIuRoP5KAH0+0w+N5YL4QoE8add0yhob\n" \
"R5Kwb3uXOuQ4Cqlhs5LNsE40dyVW9E6mqF1WBw3VeDyMhxIHHZnUkOcjIeMACC7L\n" \
"NT6dkzFsZhIv1FMuXD8fPIzv7fLcjsv4sBDJ9+MxUd5Lh52xvU/1U3CL+33COGCy\n" \
"bYFa0abDgSbzKt4gYdJ5rA+wK03+mbVHk10H2yvD769omG4aAguaUokpfoNnnlQw\n" \
"+Av1qDECgYEA9SWdYKZFmH7drQ1t1LdpZUu5QaritSwZuwd8KTUC3KSG7Bk0rs5H\n" \
"cCGknysZt+nfTe/0aIo2ZeObJlDBG/CXo143Kr5RkVgK4ktmH6RTfqg6ub1Ki5vz\n" \
"Jbe198AF+SE+G/PvzPV3nzv1F9lZu3qlp+9cHAKFOdbJTLNhB3iiLAUCgYEAyzIj\n" \
"ncKMdjfXWHDsY0Fm2Z5t+8k/pzjBpii53pDQhDOuUu5iMys988BOyHzsLMFLjjOY\n" \
"PMg1DnUVnX8ASfsC08RxBWSYQFhYhvdSvqn1DBL5aU/zuF1mthM/cT9KewkGQBmQ\n" \
"LfskNRnDmIj3xCfxVGnzAOJ28JDUV+mFqUJodyUCgYBkqMNMUjm1ejJPwnncpEsU\n" \
"mtlAy4g3WBpgn5wt12SLcMst2tO1C2Jt+oJ8ENiImfFlMSgsXMQlZiXov7PrYwkA\n" \
"vcjtNiSMB5jAfrE6QOE/2pfyeHVJigl27U48oo5RU4MLO0i14fzyV042MrsTrjKj\n" \
"GDe8EJTfwP/7DJTE2pXMeQKBgQCCxZgKdiT0CGg9cR+RmYvZzo62FwUyV+K5T0ig\n" \
"Js8r5h7xHJ5ylAfhEgkiGtPc0eIQeMAnjionTc9Fd3D2K+fb5ndeoykhcDo5Un8c\n" \
"WkFtLeD6mAwgwWvTDnwsJDGJEXvGUS1rik/5JMWvK6dZxOMaEr3j+dvWYz9l/NKa\n" \
"5jRZSQKBgQCEIqjXbyyzwlXe0+QbR8qqdaRNnp6eCdjEgXYfiSv2LpxHrWUWqF8b\n" \
"Wv2zH3R5oZTfrJNSgpmOxe3klEmRCw5y+uCSWJlj3OGOlvPltY+8daKgfmfGiQWO\n" \
"p0rJMDDXrl0MxIy8To7aS2M/zq11p8xHPN7z12xL259xHfG8gQea9g==\n" \
"-----END RSA PRIVATE KEY-----\n";

// The certificate for your device
const char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUQ+V6MJEAQCR52xY9S5tYE0zfE0owDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMTAwNjE4MjMx\n" \
"NFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMKU1z+XnGeP/cmz08El\n" \
"/tPSKDZUYJLKC2h0cYLU/9MltXD1zvH6gZZ2WE2oJdluom1JN3SMbyFrAWI/uKuy\n" \
"jN2GXvXtMgHyOY0KEngoHdvu9LtnlFUaQn+r4Kc+JT8u6IEijwXC80Aw3UNaQ3MT\n" \
"Qpc+XqN1P1mFtM+9jVaYPaUlCiW+DVdI4xxKoYg6FlAzbNnmKcmzTz41O9UWyFrT\n" \
"fNE1SqlO6Le/BzHMs+70kIlEAjTAF8PY75TdGFzQ1ZIWnmraxPH8+g2dOmcdLP68\n" \
"Yqx0pOGNvmGm7phGcTrhkFd0fMP3lK3whI7Pa2GAmLk6qH9nqOyrICHxd6T4r/3u\n" \
"r7kCAwEAAaNgMF4wHwYDVR0jBBgwFoAUvGCs2ZR6J6PCVCMO9obESG3r4B4wHQYD\n" \
"VR0OBBYEFE055rlOTopDREf0ULpwsNAeH/bTMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCeS1iFG41fksBexLBFSwFv8XVM\n" \
"tolByfo5IcolzFUAdQaF1zNIhl6fuMRMiCN+1z9k2JscELb88LPqWkHWqCrUE6xe\n" \
"cOCgo7JP6vzq9MSmYAAxpe8+g95tBCKWjaqYlpQNLp54cPLM7/82iXzxb5nI5ieE\n" \
"rDLCzE7W3YI5Pursb3fA9JAI79ykG+35Bo/9aojMHdn5S7LssleNADQ5kqFZe2fu\n" \
"WjiRpTRdgmUS9fEKEexfh+cK9zjOqJc8skjnxTXVw5MMtkZbdJYTFOrnRDuT3fwh\n" \
"y4u6ZOg2O3FolBlVDjKj19NxruG+JPqrDqILH31x45PsJINgl8rVXge2JNIX\n" \
"-----END CERTIFICATE-----\n";

#endif