# Start via `make test-debug` or `make test-release`
async def test_basic(service_client):
    response = await service_client.post('/book', params={'name': 'dostoevsky'})
    assert response.status == 200
    assert response.text == 'Here is your book: dostoevsky!\n'
