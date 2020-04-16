import requests
import json

url = "http://nginx/oauth/token"

payload = {'grant_type': 'password',
'client_id': '34726a6c-98ff-4666-b24c-96b9bcbc881e',
'client_secret': '#fljien392nf9',
'username': 'n8n',
'password': '123456789'}
files = [

]
headers = {

}

response = requests.request("POST", url, headers=headers, data = payload, files = files)

value = json.loads(response.text.encode('utf8'))
print(value["access_token"])
