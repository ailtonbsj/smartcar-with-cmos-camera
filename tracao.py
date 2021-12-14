# -*- coding: utf-8 -*-

from matplotlib.pylab import *

TRACAO_MAX = 100.
TRACAO_MIN = 900.
ERRO_MIN = 30.
ERRO_MAX = -30.

signalError = array(range(-30,31))

signalControl1 = signalError #linear
#0.037 0.04 0.05
signalControl2 = 0.037*abs(signalError)*signalError #quadratico

motor1L = TRACAO_MAX + (TRACAO_MIN-TRACAO_MAX)*((signalControl1)/(ERRO_MAX))
motor2L = TRACAO_MIN + (TRACAO_MAX-TRACAO_MIN)*((signalControl1-ERRO_MIN)/(-ERRO_MIN))
motor1Q = TRACAO_MAX + (TRACAO_MIN-TRACAO_MAX)*((signalControl2)/(ERRO_MAX))
motor2Q = TRACAO_MIN + (TRACAO_MAX-TRACAO_MIN)*((signalControl2-ERRO_MIN)/(-ERRO_MIN))
for x in range(-30,31):
    if motor1L[x] > 999: motor1L[x] = 999
    if motor1L[x] < 1: motor1L[x] = 1
    if motor2L[x] > 999: motor2L[x] = 999
    if motor2L[x] < 1: motor2L[x] = 1
    if motor1Q[x] > 999: motor1Q[x] = 999
    if motor1Q[x] < 1: motor1Q[x] = 1
    if motor2Q[x] > 999: motor2Q[x] = 999
    if motor2Q[x] < 1: motor2Q[x] = 1

subplot(2,1,1)
plot(motor1L)
plot(motor2L)
subplot(2,1,2)
plot(motor1Q)
plot(motor2Q)
show()
