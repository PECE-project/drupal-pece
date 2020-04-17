import requests
import json

url = "http://nginx/oauth/token"

payload = {'grant_type': 'password',
'client_id': 'a8e4babf-869c-4304-81a2-bdfd204805c1',
'client_secret': '',
'username': 'n8n',
'password': '123456789'}
files = [

]
headers = {

}

response = requests.request("POST", url, headers=headers, data = payload, files = files)

value = json.loads(response.text.encode('utf8'))
print(value["access_token"])
