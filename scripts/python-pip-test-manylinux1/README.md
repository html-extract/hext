# Test Hext Python Wheels with Docker

Test unpublished wheels by placing them in the ./wheels directory and running:
```
docker run \
  -it \
  --name hext-test \
  --mount type=bind,src="$(pwd)",target=/test,readonly \
  quay.io/pypa/manylinux1_x86_64 \
  /test/python-pip-test.sh
```

Test published wheels by installing them through pip (notice the parameter `use_pypi`):
```
docker run \
  -it \
  --name hext-test \
  --mount type=bind,src="$(pwd)",target=/test,readonly \
  quay.io/pypa/manylinux1_x86_64 \
  /test/python-pip-test.sh use_pypi
```

