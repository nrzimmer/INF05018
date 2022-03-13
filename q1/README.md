Serino-proteases: são enzimas que clivam proteínas, também chamadas de enzimas proteolíticas. São assim chamadas, pois estruturalmente possuem um resíduo de serina central em sua composição. A seguir é apresentado um par de serina-proteases. A primeiro (P29600) é o protease termoestável que a empresa Novozymes vende para a indústria de sabão em pó sob o nome comercial "Savinase". A outra seqüência é também uma serina-protease termoestável, mas de uma espécie diferente de Bacillus.

>P29600|SUBS_BACLE Subtilisin Savinase - Bacillus lentus
AQSVPWGISRVQAPAAHNRGLTGSGVKVAVLDTGISTHPDLNIRGGASFVPGEPSTQDGN
GHGTHVAGTIAALNNSIGVLGVAPSAELYAVKVLGASGSGSVSSIAQGLEWAGNNGMHVA
NLSLGSPSPSATLEQAVNSATSRGVLVVAASGNSGAGSISYPARYANAMAVGATDQNNNR
ASFSQYGAGLDIVAPGVNVQSTYPGSTYASLNGTSMATPHVAGAAALVKQKNPSWSNVQI
RNHLKNTATSLGSTNLYGSGLVNAEAATR

>P41363|ELYA_BACHD Thermostable alkaline protease precursor - Bacillus halodurans
MRQSLKVMVLSTVALLFMANPAAASEEKKEYLIVVEPEEVSAQSVEESYDVDVIHEFEEI
PVIHAELTKKELKKLKKDPNVKAIEKNAEVTISQTVPWGISFINTQQAHNRGIFGNGARV
AVLDTGIASHPDLRIAGGASFISSEPSYHDNNGHGTHVAGTIAALNNSIGVLGVAPSADL
YAVKVLDRNGSGSLASVAQGIEWAINNNMHIINMSLGSTSGSSTLELAVNRANNAGILLV
GAAGNTGRQGVNYPARYSGVMAVAAVDQNGQRASFSTYGPEIEISAPGVNVNSTYTGNRY
VSLSGTSMATPHVAGVAALVKSRYPSYTNNQIRQRINQTATYLGSPSLYGNGLVHAGRATQ

Considerando as sequências apresentadas, realize as seguintes atividades:

a) Implemente o algoritmo de Needleman-Wunsch para alinhamento global.

b) Realize a leitura de pares de seqüências n e m e salve o alinhamento (pares de cadeias alinhadas) e score considerando o método de Needleman-Wunsch.

(c) Apresente o score e a identidade do alinhamento.

Regras:

Valor para GAP: -4

Valor para Match: +2

Valor para Mismatch: -2

A entrega deve conter:

a) Código fonte completo e funcional. Arquivo compactado contendo todos os arquivos
fonte.
b) Arquivo PDF contendo:
1. Descrição do algoritmo desenvolvido (forma textual ou pseudocódigo)
2. Resposta para a letra ”b”
3. Resposta para a letra ”c”