#!/bin/bash

mkfifo krm_rac
mkfifo rac_krm

./rac <krm_rac >rac_krm &
./krmilnik <rac_krm >krm_rac &


rm krm_rac rac_krm