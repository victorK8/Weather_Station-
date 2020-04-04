import requests


AEMET_OpenData_Key = 'eyJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ2aWN0b3JtYWx1bUBnbWFpbC5jb20iLCJqdGkiOiJlMTBlNmQ3Zi01ZGMxLTQ4YjMtODgwMi1iOTBmNWJlYWU0OWMiLCJpc3MiOiJBRU1FVCIsImlhdCI6MTU4NjAxNTY5NywidXNlcklkIjoiZTEwZTZkN2YtNWRjMS00OGIzLTg4MDItYjkwZjViZWFlNDljIiwicm9sZSI6IiJ9.8Pasy8u3zx_f4XWZifJrO0F2KMsims1ZDMf-8VRbRjo' 


url = "https://opendata.aemet.es/dist/index.html?#!/valores-climatologicos/Climatolog%C3%ADas_diarias"


querystring = {"api_key":"eyJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJqbW9udGVyb2dAYWVtZXQuZXMiLCJqdGkiOiI3NDRiYmVhMy02NDEyLTQxYWMtYmYzOC01MjhlZWJlM2FhMWEiLCJleHAiOjE0NzUwNTg3ODcsImlzcyI6IkFFTUVUIiwiaWF0IjoxNDc0NjI2Nzg3LCJ1c2VySWQiOiI3NDRiYmVhMy02NDEyLTQxYWMtYmYzOC01MjhlZWJlM2FhMWEiLCJyb2xlIjoiIn0.xh3LstTlsP9h5cxz3TLmYF4uJwhOKzA0B6-vH8lPGGw"}

headers = {
    'cache-control': "no-cache"
    }

response = requests.request("GET", url, headers=headers, params=querystring)

print(response.text)
