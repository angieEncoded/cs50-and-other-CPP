import re
dnaToSearch = "AATCCTGGTTGGACATACCGTTTTCCACACAAATGCCCCAGACACTGTACGGAGACCCTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTCTAGTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTTTTTTTCTAAGAACCGGGGTTTTGGCTGATTCACCGAGTCAACCTAAGACACTAGTTAAACATGTTTGTCGATTATATCACCTTTCATATATTCCGAGCGACACTTTTCAATGCTATATGGTGCTTATTCCTGCTTACCATTTTCGGACCCAGGCCTCAACTTTTGCTTGTACGACATGAAAGGTGCAGCTCTACTTGGATAAGGTGTACTACCTAGCTTACTCGCACCGGACCATTAGCTATTACAGGGTTTGGATAGTTACGTGATGATCGAGGCAGACACCGTAAGACTCTTACGCGCCCGACGGTCCCCGTTAATGATGACAGTGACGAAAGGATTGAGAGGCGCGTCAGACCCCTGTTCCCATATTGTATGTTGTCGTTGGTACGGGCGCCTTACGGAGTAAGGTGTTAGGCAGGAATGGCCAAAGGTTGGTGAACCTGAATCATGGTTGACACGCAGCTCTCTACATTTATGGGCGTATTCCTATTCGCGACTACTACAACTCTTCGGCCGCCGGTAACCGTACGGTGGCTAGATGCCGCTCATACAAAGTATGCGAGCCGTATTCAGAGTATAATGACCTGAAGGAGTACATGAGGGTCATGGTCCGCAGGGACTCCCTGTCATATGCTGAGATGGAGCCATAATCCCTGCCAGCCGTGTGGACTCAGGCATTCCTGTATTAAGCACTCTAGCCCTCGTGAATGCTTGGAAGAGTCACCCAAGGAATCGATTATCACAGGTTGGGAGAGGATGTTTTTCAAGGCCCTGAAAATTTGAAGGGGCTATTGACTGCGGCGTTACAACCAAAGAGATGACGGAACCATTGCTTCCGTCATGCTGGTGTCCCTGTGCGACCCACCGTGTTTGCTCCAATAAGTGGAAGGGTAAATTGATTACTACCGGTTTCATAGGAAGTTCGAGGTGCACGGTTGAGTAGCATTAGAGCTTCGAGCCAGGTTACCATAGTTATCTTTATGGGGCACTCGCCCTGATGTTTACGCCAGGGTTTAGCTTTGTGATCCGTTAGGGGGTTACCTACGACGCAGCAATTAGCGGGTGTCGCAGGTGTGTAGTTTGTGGCACCAAGCCAGCGGGCTTTACTTAACCAACCCTGGGAAGATCACTTCATCCGAATATGAGATCGCCCAACGCTAATACGCCGAAATGGGAACTGAAGGTCTTAGACTAGCTCACGAACCGTATACCTTAAGTTCCCTAAGCGGACGAATTTTTACTAAGTAAGGATTGCAGGAATATGGAAATCATCCGTACGTGCTTTGACGACCCAAAAAGAGGATCAATGGTATCTACCCAAAGCGTTATTCCTAGTACCAGGAGCCTAAATCATTTATAAAAAAATGCAACCTTTACCGTGGAGCGAAGGAAACTCTACTTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTATCTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGTCTGGTGTCAACCGTAGCCTGGTAGATGGAGGATGGTCGACTGGCTCAGATCCACCCTTGTGGCGGCATAACAAAATGTTCACTGAATTGGGCGAAAAATTAGCGAGTGTCACTTGACAAGGACTGAATAGCAGCAACAACCGTCGAGATCGTTGTCCAGTCACGCGGACTGATGATCTTAGATATAACGCAGAACTCAATGGCTCCTCCTGTACTATGATAGGGCGATATAGCGAGCCGAAAACTCGGGCCGGATGAGCGCTCACTGCGGTCCCGCAGCGCTGTTACGACGCCACGTTACCCTTGATCCGTGGTTGGTAGTGTCGCGTGATGAATGCACGAGTTGGTACCGTTCTAAGATCGACTACACGTGGCTCGATTTTAGCAAGTGTGCGATACCTGAATAGTCTGTAACAGTCCGGCGACCCATGGAAGCCGTTTCGTCCCGTATGCCAAGGCCCCGTTTATCCCTCAGCATGGGAATGACGGCCACCAGTGGTCCGTGTTCGCGATCAGTCTCGGGGAGGTACACACCCTCACTGTAAACTGGCAAGGAGGTGATTTTGCCCAATCTGAGAGCCTAAAGTGGCAGTACAGGTTCCTCACACATAACGAGGTACTTGCCTAACTACGTCCTATGTAGACAGGATAAGAAAACGCAGAGCGCGACCGCCGTGCAGTAATGAGTACTAAGGTAACTGGCCGCTCATATGTTCAGTACTGTCACCGTGTTGGTTAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAAGAAATCGACGCTAAGTCGGCTTCAGACTCTTGCGATGATTCCGATTCGGCCTTTTCCCTCAGTGCTTCTCAGCAGGCAACTTGCGAAAAGCATATCGCGCATTAGTACAACAGCAATTACTACACGACCAAAACGTCGTGGAGAGTCGCTGTACTGCAGCTCAAGGGTGGCCGACCATAGAACATTTAACGATATGCACGATCCGGTCAAATATCACAACAGAATTGTGTGCTAGTAGGGGAAAAGGGGAAGGCCCTTCCTTGGGATAGATAGATAGATAGATAGATAGATAGATAGATAGATAGATAGATAACCGACTCATTGCGGAATTTTCAGTTTTACAATGCGGTGACCACTAGCCAACGGCGTCATTGATAATGATACTAACTTCCTTGGGGCGACTCCGGTTTAAAAGTGGCCGGTACGCTTGTTCGACATCATGTGTAGCGTTATTAGGACTGAATTACCGGGCCCCGTTCCGAGATGTTCTTTTTCGGCCCCTGGCGCAGAGGCGCTTGAGCTGCATATACTGGAATATAAGAGGTCACTCGCGAGAACGGTCACGCTACCATGTCGGCAGGATGCAGGATCAGGAATAATGTGGTAGACCTGTGTTCAACGGTGATCTCGGTGTGGATCGGGTGAGCACCAGATCGACTAACTAAGGGATATGCAAGCAGATTCTTCGGACGCCTTTGCCGGTAACACATGGAACACGCCTATGCGCTCCATTACTGGGTGCCTTGTTGAGACGGATAGGTCGGGTTCAATGATTATTAAGGTTTATCAACGTATTACTGCTTGTAACGGCTTGTAAGTGCCAATTGTCATTCGACCCCGGCTGGTCTGACAAGGTTTGTACGCCGATTTGGCATGAGGGGACTAGAGTGGAATAGGATTGTGCACTAAGCTGCGGTCCCGCCTGCGTACCCGCGTATCAAGTGGCTCGGTGGCTGGTTGCGATTACTGAGCTCGTGCATTGCTATCAGTGCGTCCCCTGCAAGAACAGGTATCAAGTGTGGTTCCGTATTGCACGATTGACAATTTCATCGGGTATTCGCTCGTCGGCAAACATTGAAGGCTTCATAGGTTCACAACCGCGTTCCCTGTGATGCGGAATCGCGAGATCTGGATCATCCTTCTAAGACACTCAAAATGCAGACGTCGAGAGACGTATGCGTCCGCGGGAACTATGGCATCTGCCCTTAACATGTGAAGAGACTGCTTTAGCTCGATCTAACCGTAGGCCCTTCATGAAGAGAAGCCATTGTCGGGGGTAGTGACTTTTGGCCGTACGTGATTAAATAACACGGAGTCAAACTCGGAGCGTTCCGTCTCTGATATCGCCAACATCGCAAGCTCCCTACGTACCACCCTGGGTGAACACGACTTTAATGCTTTGAAAATATTGATGGAGACGGCACAAATTTCCGAAAACTCGAAACTTAGTAAATTTACACTGAAAAACCCGGGCGGACAAGTACAAGAGTCCGCGCTCGTAGTGCTCTGTTGAAGCGTTGACCTCTGTCGCTTAAAATCGTAAAGACTTTATACACGAATATTGAGTGAGAAAGAGTCCCCGATCTATCATTACAAATATTCCGTTCTACAATCTGAGGCCAGACAGTTTTGTTCCCTCTCCTTACCTAGTGCCATATCGAGGGACAGAAATTTGACACCTTGCAGTCACACGTTGTTTTGAGATATGCAAACCACGCCCAGTGTCGAGATCCCACATATCTTCATTATAAGCTCGACCACTTGAGACTGCAGCACGAAGGCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGATCAGAAATTCCAAGCAATGGCTTCAGCGCTCGGACGCCCCGCCCGTGCCCGGCGTGAACATATGGATGTATGAATTATTGCATGGTCTGTATCTTAATGCGCGCTTGGCAACACATGTGAGAACGGTCTCACGTGCGACTACGTATGATCTATGCAAATGTGCGGTGGCGCCCGGCCTTTTTAGGAGGTTCCTAGACCAGGAGCCTGTGTGGTAAGGGCCGGCAGACGTTTCCGGTACGCTCCGCCAAGAAGGTAACCATGCGGCCCGGTAATGTAACCAGGTCTCGAAAAAATTAGGCGAATCGAAAGGGTTCTATCGGACCGTTAACAATTTACGGTCATTCTAGTATGCATTCAAGGAACCGACTCTCGTCTCACATTTATGTCATCATTATGACTAACGCAAGCTGTTACAACGTGACTACTCACCTGGATCGTCATCACGCGCGATGTGCATGAACTCGCAAAAACGAACCTAATCGAACGGTTATCGGTGACATTTGATTTTGAGTCTGCGGCACGTAAAAGCTCTGGGATGCAGCTCCTATATCAGCCTAGGGGTCGGGCTCTCTGGTTCTGCTCGCTAGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGAATGCAGTCCCGTGAGTGAGTAGTATACGCGATCTTGTGTGTCTAAGTTATTGCCACACACGAATGACCAAATACGAGATCTAGACTCGTGTATATGAGACAGGTTGCACAATCAGCCTTTATTCTGAGACAGTGGTGCTGGGGATGGCTTGAGATACATACGCACACAAGCCCAGGGGGATTAATTGCTGCGCAGATAGCCCGCCCAAAGTTGTCCCAGTGACCTTAGAAGGACCCTGTACCTGGCGTTGGGTAAGACACGTCACCCGTCGTAGCCGTGTATAGCCGAGCGTCCTGCAAAAGCGTATCTTTTTGATGAGCGAAATCGCGTCCAAAGACTTCGCTCAATTCAGAAGGCTCGAATTGCCGATCGTCGCAGGGCTGCATTAGGCACGCCAGTTCTTCTAGGTCCCGGGCCGAGAGTGTTCGGCGGTAACTGCCTTTTAGGGGCCGCACACCTCGGCTGCGGCCGGGCGGAAGGCGCTTACTTCTGGATGCGGCTTCAGACGGCTGTAATATGTCTCGGAATACCGCTCAGCATACGAGGAGTCTCCGCTTTCGACAGCCTGGGGCCACGTCGTGTTGAA"
whatToSearchFor = "TATC"

# Search the string with a regular expression. Using String interpolation (formatted strings) to get my variable in
# This tells it to search the string for the item in question and match one or more occurrances
# I got the idea from the discord searched for help with regex and ended up here https://stackoverflow.com/questions/61131768/how-to-count-consecutive-repetitions-of-a-substring-in-a-string
# and here https://regex101.com/

totals = re.findall(rf'(?:{whatToSearchFor})+', dnaToSearch)
print(totals)
largest = max(totals)
print(len(largest) // len(whatToSearchFor))
