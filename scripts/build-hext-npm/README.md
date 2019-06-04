# Build Hext npm packages with Docker

```
docker run \
  -it \
  --name hext-npm-build \
  --mount type=bind,src="$(pwd)",target=/build \
  thomastrapp/static-build-env-jessie \
  /build/build-hextjs-linux.sh
ls -lah output/
```

