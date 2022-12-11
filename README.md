# group_2

Jäsenet: 

Kolehmainen Niko, Virta Emilia, Mäki Jussi, Lampinen Roosa, Rantanen Tero

Projektin alussa sovittiin että kaikki haluaa oppia itse tekemällä asioita jokaisesta työvaiheesta
joten emme suorittaneet varsinaista työnjakoa aluksi, vaan päätettiin että kaikki tekee 
toimivan raakaversion jossa backendin login kryptayksineen toimii ja frontissa alkeellinen
logintoiminto. Tämän jälkeen jokainen teki itsenäistä tutkimustyötä ja kokeiluja frontin olioiden välisen 
informaationkulun välillä. Kokeiltiin ratkaisuja singletonin kanssa, kokeiltiin pointtereiden periyttämisillä
yms. Haluttiin tehdä demo-ohjelmasta jo sellainen malliratkaisu jota ei tarvitse sulkea välissä vaan
voi kirjautua useilla korteilla peräkkäin ja jättää ohjelman päälle kuin se olisi automaatissa. 

Päädyttiin ohjelmassa olevaan ratkaisuun tiedonkulun ja ikkunahallinnan kanssa.

Tämän jälkeen tehtiin selkeämpi työnjako ja asioita jaettiin ikkunaoliokohtaisesti.
Jokainen toteutti työnjaon mukaiset oliot fronttiin ja niiden tarvitsemat backend osiot.
Kaikkien tekijöiden versiot kommeltiin kasaan "Rantanen" branchissa jossa tarkististettiin että 
kaikki päivitykset toimii ohjelman logiikan kanssa ennen kuin se ajettiin Mainiin. 

Tästä syystä näyttää että lähes kaikki merget on tulleet "Rantanen" branchin kautta.
Päivityksiä muilta tekijöiltä "Rantanen" branchiin ei usein tehty mergellä, 
vaan .h, .UI ja .cpp tiedoston tekstit lisättiin/päivitettiin 
tekijän branchista.
