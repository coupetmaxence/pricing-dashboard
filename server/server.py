#!/usr/bin/env python

import asyncio
import websockets
import subprocess
import json
import requests
import pandas as pd
import urllib.request as urllib2
from bs4 import BeautifulSoup


async def hello(websocket, path):
    message = await websocket.recv()
    print("< {}".format(message))

    # TODO : check data, etc
    json_file = json.loads(message)
    
    json_data = requests.request('GET', 'https://www.alphavantage.co'+
                        '/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol='+json_file['data']['underlying'][0]+
                        '&apikey=KNZX').json()
    json_string = json.dumps(json_data)
    
    data_frame = pd.read_json(json.dumps(json_data["Time Series (Daily)"]),orient='index')
    data_frame_pct = data_frame.pct_change()    
    
    site_global = "http://www.global-rates.com/interest-rates/libor/american-dollar/usd-libor-interest-rate-"
    if(json_file['data']['maturity'] == '6 months'):
        site_global += '6-months'
        maturity = 0.5
    else:
        site_global += '12-months'
        maturity = 1.0

    site_global += ".aspx"
    hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

    req = urllib2.Request(site_global, headers=hdr)
    page = urllib2.urlopen(req)

    soup = BeautifulSoup(page, "lxml")
    
    table = soup.find('table', style="width:208px;border:1px solid #CCCCCC;")
    libor = table.find('tr', class_='tabledata1').find_all('td')[1].text
    libor = float(libor[:6])/100
    
    running_json = {}
    running_json['meta'] = json_file['meta']
    running_json['data'] = {}
    
    running_json['data']['price'] = data_frame["5. adjusted close"][0]
    running_json['data']['std'] = data_frame_pct[["5. adjusted close"]].std()[0]*(252**0.5)
    running_json['data']['risk_free'] = libor
    running_json['data']['maturity'] = maturity

    with open('../pricer/message.json', 'w') as f:
        json.dump(running_json, f)    
    
    result = subprocess.run(['../pricer/main', 'param'], stdout=subprocess.PIPE)
    result_message = result.stdout.decode('utf-8')

    await websocket.send(result_message)
    print("> {}".format(result_message))

start_server = websockets.serve(hello, '89.234.182.19', 8765)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
