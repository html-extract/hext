# Build Hext Python Wheels with Docker

```
docker run \
  -it \
  --name hext-test \
  --mount type=bind,src="$(pwd)",target=/build \
  thomastrapp/static-build-env \
  /build/build-hext-python.sh
ls -lah output/
```

