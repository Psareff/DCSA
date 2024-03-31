curl -X POST -d '{"id": "123", "info": "Some useful info", "name": "John"}' http://localhost:7777/user
echo
curl -X POST -d '{"id": "456", "info": "More useful info to God of useful info", "name": "Michael"}' http://localhost:7777/user
echo
curl -X GET http://localhost:7777/user/John
echo
curl -X GET http://localhost:7777/users
echo
curl -X DELETE http://localhost:7777/user/John
echo
curl -X GET http://localhost:7777/users
