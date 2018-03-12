#!/usr/bin/env python

import asyncio
import websockets
import subprocess
import json
import requests
import pandas as pd

def hello():
    json_data = requests.request('GET', 'https://www.alphavantage.co'+
                        '/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol='+'AAPL'+
                        '&apikey=KNZX').json()
    json_string = json.dumps(json_data)

    data_frame = pd.read_json(json.dumps(json_data["Time Series (Daily)"]),orient='index')
    data_frame_pct = data_frame.pct_change()
    #data_frame_pct[["5. adjusted close"]].plot()
    print( data_frame_pct[["5. adjusted close"]].std()[0]*(252**0.5))

hello()
