import aiohttp
import asyncio
import json
from prywatne import API_key

async def fetch_page(session,url,params=None):
    async with session.get(url, params=params) as result:
        res = await result.text()
    return res

url1 = "https://api.magicthegathering.io/v1/cards" #bez API key
url2 = "https://api.thecatapi.com/v1/images/search" #z API key (randomowe zdjecie kota)

async def main1():
    async with aiohttp.ClientSession() as session:
        request = fetch_page(session, url1)
        result = await asyncio.gather(request)
        data = json.loads(result[0])
        return data["cards"][0]["name"]

async def main2():
    async with aiohttp.ClientSession() as session:
        params = {"x-api-key": API_key}
        request = fetch_page(session, url2, params)
        result = await asyncio.gather(request)
        data = json.loads(result[0])
        return data[0]["url"]

print(asyncio.run(main1()))
print(asyncio.run(main2()))
