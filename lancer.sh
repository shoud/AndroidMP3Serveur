#!/bin/sh

glacier2router --Ice.Config=ICEStorm/glacier.service &
icebox --Ice.Config=ICEStorm/storm.icebox &
./serveurMP3
