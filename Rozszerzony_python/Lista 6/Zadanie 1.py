import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin

def crawl(start_page, distance, action):
    visited_pages = set()

    def process_page(url, current_distance):
        if url in visited_pages or current_distance < 0:
            return

        visited_pages.add(url)

        try:
            response = requests.get(url)
            response.raise_for_status()
            content = response.text

            result = action(content)
            yield (url, result)

            soup = BeautifulSoup(content, 'html.parser')
            links = [link.get('href') for link in soup.find_all('a', href=True)]
            for link in links:
                absolute_url = urljoin(url, link)
                yield from process_page(absolute_url, current_distance - 1)

        except Exception as e:
            print(f"Error processing {url}: {e}")

    yield from process_page(start_page, distance)

start_page = "https://www.python.org/events/python-events/"
distance1 = 0
distance2 = 1

print("Dla dystansu 0:")
for url, result in crawl(start_page, distance1, lambda text: "Python" in text):
    print(f"{url}: {result}")

print("Dla dystansu 1:")
for url, result in crawl(start_page, distance2, lambda text: "Python" in text):
    print(f"{url}: {result}")