from html.parser import HTMLParser  
from urllib.request import urlopen  
from urllib import parse

class LinkParser(HTMLParser):

    def handle_starttag(self, tag, atributi):
        if tag == 'a':
            for (key, value) in atributi:
                if key == 'href':
                    noviURL = parse.urljoin(self.baseURL, value)
                    self.links = self.links + [noviURL]

    def getLinks(self, url):        
        self.links = []
        self.baseURL = url
        response = urlopen(url)

        if response.getheader('Content-Type') == 'text/html':
            htmlBytes = response.read()
            htmlString = htmlBytes.decode("utf-8")
            self.feed(htmlString)
            return htmlString, self.links
        else:
            return "", []


def crawler(url, maxBrojStranica):

    potrebnoPosjetiti = [url]   # Backlog - FIFO lista
    brojPosjećenih = 0

    spremnik = open("Linkovi.txt", "w")

    while brojPosjećenih < maxBrojStranica and potrebnoPosjetiti != []:

        brojPosjećenih += 1
        url = potrebnoPosjetiti[0]
        potrebnoPosjetiti = potrebnoPosjetiti[1:]   # Odreži prvi url

        try:
            print(brojPosjećenih, " Posjećujem: ", url)
            parser = LinkParser()
            data, links = parser.getLinks(url)
            spremnik.write(url + "\n")
            for link in links:
                spremnik.write(link)
                spremnik.write("\n")
            spremnik.write("---\n")
            potrebnoPosjetiti = potrebnoPosjetiti + links
            #print("  *Uspjeh*")
        except:
            print("  *Preskačem*")

def main():
    crawler("http://www.meteo.hr", 20000);     # Početni link

if __name__== "__main__":
    main()