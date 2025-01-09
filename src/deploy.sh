#!/bin/bash

REMOTE_HOST="172.24.116.8"
REMOTE_USER="user4"
REMOTE_DIR="/usr/local/bin"

scp src/cat/s21_cat $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR
scp src/grep/s21_grep $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR

if [ $? -ne 0 ]; then
  echo "Ошибка при перемещении файлов!"
  exit 1
fi

echo "Файлы успешно скопированы!"