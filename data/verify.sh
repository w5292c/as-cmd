#!/bin/bash

openssl cms -verify -in signature.p7s -inform der -content plain.txt -CAfile /etc/ssl/certs/COMODO_RSA_Client_Authentication_and_Secure_Email_CA.pem
