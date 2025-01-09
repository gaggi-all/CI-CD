#!/bin/bash

STAGE_TYPE=$1
BOT_TOKEN="7029559554:AAFfop-qngmiwLakQYnZa81t5xm7O8QEKj8"
CHAT_ID="492867280"

sleep 5

if [ "$CI_JOB_STATUS" == "success" ]; then
  MESSAGE="Стадия $STAGE_TYPE $CI_JOB_NAME успешно завершена ✅ $CI_PROJECT_URL/pipelines"
else
  MESSAGE="Стадия $STAGE_TYPE $CI_JOB_NAME завершилась с ошибкой! 🚫 $CI_PROJECT_URL/pipelines"
fi

curl -X POST "https://api.telegram.org/bot$BOT_TOKEN/sendMessage" -d chat_id=$CHAT_ID -d text="$MESSAGE"