# Build stage
FROM alpine:3.17 AS builder

# Install build dependencies (only necessary ones)
RUN apk add --no-cache cmake g++ make git

# Set working directory
WORKDIR /opt/sources
COPY . .

# Build the application with static linking
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" .. && \
    make && ctest --output-on-failure && \
    strip --strip-all dit639_group14 && \
    cp dit639_group14 /tmp/

# Final minimal image
FROM scratch

# Copy the compiled binary
COPY --from=builder /tmp/dit639_group14 /dit639_group14

# Set entrypoint
ENTRYPOINT ["/dit639_group14"]
