

Deploy local docker registry directly with Docker

    docker volume create local_registry
    docker run -d --name registry.local -v local_registry:/var/lib/registry --restart always -p 127.0.0.1:5000:5000 registry:2


Install k3s

    curl -sfL https://get.k3s.io | sh -

Copy the `~/.kube/config` file from `/etc/rancher/k3s/k3s.yaml` to the client machine
and modify the server URL to match the address of Raspberry Pi on the local network.



Build custom node-red image

    git clone git@github.com:tsaarni/node-red-docker.git
    cd node-red-docker/docker-custom/
    docker build --file Dockerfile.custom --tag localhost:5000/node-red:latest .
    docker push localhost:5000/node-red:latest


Deploy all services

    kubectl apply -f manifests


Initialize influxdb

    kubectl exec -it $(kubectl get pod -lapp=influxdb -o jsonpath='{.items[0].metadata.name}') influx
    > CREATE DATABASE home


## Tips

K3s volumes can be directly accessed on host under directory `/var/lib/rancher/k3s/storage/`



