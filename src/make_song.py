cbaes_notes = {
    1   : ['C4', 261.63],
    1.5 : ['C4#', 277.18],
    2   : ['D4', 293.66],
    2.5 : ['D4#', 311.13],
    3   : ['E4', 329.63], 
    4   : ['F4', 349.23], 
    4.5 : ['F4#', 369.23],
    5   : ['G4', 392.00],
    5.5 : ['G4#', 415.30],
    6   : ['A4', 440],
    6.5 : ['A4#', 466.16],
    7   : ['B4', 493.88]
}
two_tiger = [
  [1, 2], [2, 2], [3, 2], [1, 2],
  [1, 2], [2, 2], [3, 2], [1, 2],
  [3, 2], [4, 2], [5, 4],
  [3, 2], [4, 2], [5, 4],
  [5, 1], [6, 1], [5, 1], [4, 1], [3, 2], [1, 2],
  [5, 1], [6, 1], [5, 1], [4, 1], [3, 2], [1, 2],
  [3, 2], [-15, 2], [1, 4],
  [3, 2], [-15, 2], [1, 4]
]
f_cpu = 11059200
test_song = two_tiger
do_base = 'F'

# note:
#   assume 1 = C
#   1, 2, 3 present C4, D4, E4
#   11, 21, 31 presetn C5, C6, C7
#   -11, -21, -31 present C3, C2, C1
#   add .5 means add a semitone
def map_note (num, base = 'C'):
    base_table = {'C':0, 'D':2, 'E':3, 'F':4, 'G':6, 'A':8, 'B':10}
    if num == 0:
        return 0
    octave = int(num / 10)
    note_family = abs(num) % 10
    c = note_family
    if (num % 1 > 0):
        c += 1
    c += base_table[base]
    if c > 7:
        c -= 7
        octave += 1
    return cbaes_notes[c][1] * 2**octave

# freq_table:
#   e.g: 6:[0, 251, 232]
#     6: num name in music;
#     0: index of this freq, it will be used in c code;
#     [251][232]: th and tl value about a freq, this is 'A4'(440Hz).
#   
def make_freq_table (song):
    freqs = []
    table = {}
    index = 1
    freqs.append(0)
    table[0] = [0, 0, 0]
    for note in song:
        freq = map_note (note[0], do_base)
        if freq not in freqs:
            th = int(65536 - (1000000/freq/2)*f_cpu / 12000000) >> 8
            tl = int(65536 - (1000000/freq/2)*f_cpu / 12000000) & 0x00FF
            table[note[0]] = [index,  th, tl]
            freqs.append(freq)
            index += 1
    print(table)
    return table

def make_freq_table_c (table):
    freq_list = []
    notes = table.keys()
    for i in notes:
        freq_list.append([table[i][0], table[i][1], table[i][2]])
    freq_list.sort(key = lambda x:x[0])
    c_code = ""
    c_code += "static Freq freq_table[] =\n"
    c_code += "{\n"
    for i in freq_list:
        c_code += "  {{{th}, {tl}}},\n".format(th = i[1], tl = i[2])
    c_code += "};\n"
    return c_code
        
def encode_song (song, table):
    c_code = ""
    c_code += "static Song test_song[] =\n"
    c_code += "{\n"
    for i in song:
        c_code += "  {{{index}, {length}}},\n".format(index = table[i[0]][0], length = i[1])
    c_code += "};\n"
    return c_code


freq_table = make_freq_table(test_song)
print(make_freq_table_c(freq_table))
print(encode_song (test_song, freq_table))
