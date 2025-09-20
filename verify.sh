#!/usr/bin/env bash

competitive-verifier oj-resolve >verify.json && competitive-verifier verify --verify-json verify.json >result.json
