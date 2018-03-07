#docker run -d -it --rm -u $UID -v ~/mywork:/mnt debian /bin/bash -c 'cd /mnt; ./run.sh'
#docker exec -it --rm -u $UID -v ~/mywork:/mnt debian /bin/bash -c 'cd /mnt; ./run.sh'
docker run  --rm --user $UID:$(id -g) -v ~/mywork:/mnt debian bash -c 'cd /mnt; touch d1234567890; echo --------------'
ls ~/mywork/d123* -al
rm ~/mywork/d123*
