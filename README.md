# FEUP-CAL

## Routing multimodal para transportes coletivos
#### Primeira Parte
A multimodalidade tem-se estabelecido como um fator de atratividade para a mobilidade em transporte público, oferecendo uma grande variedade de modos de transporte, incluindo metro, autocarros, comboios urbanos, interurbanos e regionais. Apesar disso, os sistemas de navegação em transporte públicos não tiram partido da combinação dos vários modos.
Implemente um sistema de navegação capaz de gerar opções de itinerário entre uma origem e um destino considerando a combinação de diferentes modos, em trechos distinto do itinerário. Por exemplo, alguém poderá desejar realizar a primeira parte da viagem de metro, seguindo na restante parte em autocarro. Entretanto, ainda será necessário realizar trechos a pé, até as paragens respectivas. O sistema deverá ser capaz de contabilizar o tempo de viagem para cada trecho (a pé, autocarro, metro, etc.), assim como as diferenças possíveis no tarifário. O utente também poderá desejar favorecer um ou outro modo de transporte, ou poderá estabelecer limites para as tarifas a pagar.
Avalie a conectividade do grafo, a fim de evitar combinações de modos que não são compatíveis, ou que exijam um percurso a pé demasiado extenso, comparativamente ao percurso total da viagem.

Utilize mapas reais, extraídos do OpenStreetMaps (www.openstreetmap.org), localizando, no mapa, as diferentes linhas dos serviços de transportes, paragens, e estações de transbordo.

#### Segunda Parte
Para a segunda parte deste trabalho, extenda o trabalho realizado com funcionalidades apropriadas que permitem a consulta da existência ou não de uma determinada paragem ou estação. Implemente esta funcionalidade, considerando tanto pesquisa exata, assim como pesquisa aproximada, das strings identificativas dos nomes das paragens e estações. Para pesquisa exata, caso os nomes procurados não correspondam a paragens e estações existentes, deverá retornar mensagem de lugar desconhecido. Para a pesquisa aproximada, deverá retornar os nomes de paragens e estações mais parecidos com o nome procurado, ordenados por similaridade.

Estas novas funcionalidades deverão ser integradas no trabalho já realizado para a primeira parte. Avalie a complexidade (teórica e empiricamente) dos algoritmos implementados em função dos dados de input usados.
