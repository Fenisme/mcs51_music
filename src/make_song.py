import config
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

f_cpu = config.f_cpu
breathe = config.breathe
tones_per_min = config.music[2]
tones_per_section = config.music[3]
min_tone = config.music[4]

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
    while c > 7:
        c -= 7
        octave += 1
    return cbaes_notes[c][1] * 2**octave

# freq_table:
#   e.g: 6:[0, 251, 232]
#     6: num name in music;
#     0: index of this freq, it will be used in c code;
#     [251][232]: th and tl value about a freq, this is 'A4'(440Hz).
#   
def make_freq_table (song, do_base = 'C'):
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
    return table


def make_freq_table_c (table, index):
    freq_list = []
    notes = table.keys()
    for i in notes:
        freq_list.append([table[i][0], table[i][1], table[i][2]])
    freq_list.sort(key = lambda x:x[0])
    c_code = ""
    c_code += "static const Freq freq_table{}[] =\n".format(index)
    c_code += "{\n"
    for i in freq_list:
        c_code += "  {{{th}, {tl}}},\n".format(th = i[1], tl = i[2])
    c_code += "};\n\n"
    return c_code

# def need_continuity (length):
    # if length > 7:
        # return 1
    # else:
        # return 0

def encode_song (song, table, index = 0):
    tones = 0
    section = 1
    c_code = ""
    c_code += "const static Song song{}[] =\n".format(index)
    c_code += "{\n"
    c_code += "  "
    for i in song:
        if tones > tones_per_section:
            c_code += " /* {} */ \n".format(section)
            c_code += "  "
            tones -= tones_per_section
            section += 1
        tmp_length = i[1]
        while tmp_length > 0:
            # c_code += "{{{continuity}, {length}, {index}}},".format(continuity = need_continuity (tmp_length), index = table[i[0]][0], length = min(tmp_length, 7))
            c_code += "{{{length}, {index}}},".format(index = table[i[0]][0], length = min(tmp_length, 15))
            tmp_length -= 15
        tones += i[1]
    c_code += "\n"
    c_code += "};\n\n"
    return c_code

# timer:
#   This func is used to generate count value for time counting.
def timer_setting(tones_per_min, tones_per_section, min_tone):
    tones = tones_per_min * (min_tone / 4)
    song_meter = int(60000/tones)
    breathe_meter = int(breathe * 60000/tones)
    velocities_th = "#define VELOCITIES_TH {}\n".format(int(65536 - 1000 * f_cpu / 12000000) >> 8)
    velocities_tl = "#define VELOCITIES_TL {}\n".format(int(65536 - 1000 * f_cpu / 12000000) & 0x00FF)
    return velocities_th, velocities_tl, song_meter, breathe_meter

def make_music_h(songs):
    h_code = "#include \"song.h\"\n"
    index = 0
    length = []
    meter = []
    breathe = []
    th = ''
    tl = ''
#tones_per_min = config.music[2]
#tones_per_section = config.music[3]
#min_tone = config.music[4]
    for s in songs:
        length.append(len(s[0]))
        th, tl, b, c = timer_setting(s[2], s[3], s[4])
        meter.append(b)
        breathe.append(c)
        freq_table = make_freq_table(s[0], s[1])
        h_code += make_freq_table_c(freq_table, index)
        h_code += encode_song (s[0], freq_table, index)
        index += 1
    h_code += "static const Freq *freq_tables[] = {"
    for i in range(index):
        h_code += "freq_table{}".format(i)
        if i != index - 1:
            h_code += ", "
    h_code += "};\n"

    h_code += "static const Song *songs[] = {"
    for i in range(index):
        h_code += "song{}".format(i)
        if i != index - 1:
            h_code += ", "
    h_code += "};\n"

    h_code += "#define SONG_INDEX_MAX {}\n".format(index - 1)

    h_code += "static const unsigned int song_length[] = {"
    for i in range(index):
        h_code += "{}".format(length[i])
        if i != index - 1:
            h_code += ", "
    h_code += "};\n"

    h_code += "static const unsigned int song_meter_table[] = {"
    for i in range(index):
        h_code += "{}".format(meter[i])
        if i != index - 1:
            h_code += ", "
    h_code += "};\n"

    h_code += "static const unsigned int song_breathe_table[] = {"
    for i in range(index):
        h_code += "{}".format(breathe[i])
        if i != index - 1:
            h_code += ", "
    h_code += "};\n"
    h_code += th
    h_code += tl
    return h_code

songs = config.musics
print(make_music_h(songs))
