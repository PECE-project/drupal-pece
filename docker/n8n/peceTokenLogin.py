import requests
import json
import os

url = "http://nginx/oauth/token"

payload = {'grant_type': 'password',
'client_id': os.getenv('N8N_CLIENT_ID') if os.getenv('N8N_CLIENT_ID') else '',
'client_secret': os.getenv('N8N_CLIENT_SECRET') if os.getenv('N8N_CLIENT_SECRET') else '',
'username': os.getenv('SITE_N8N_USERNAME') if os.getenv('SITE_N8N_USERNAME') else '',
'password': os.getenv('SITE_N8N_PASSWORD') if os.getenv('SITE_N8N_PASSWORD') else ''
}
files = [

]
headers = {

}

response = requests.request("POST", url, headers=headers, data = payload, files = files)

value = json.loads(response.text.encode('utf8'))
print(value["access_token"])
