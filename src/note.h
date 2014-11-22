#ifndef NOTE_H
#define NOTE_H

struct Note
{
    int num;
    enum NoteType {none, dong, ka, dong_big, ka_big,
                renda, renda_big, balloon, end}
               noteType;
    int parameter_i;

    inline bool operator<(const Note& note) const
    {
        return num<note.num;
    }
    inline bool operator==(const Note& note) const
    {
        return num==note.num;
    }
    inline bool operator>(const Note& note) const
    {
        return num>note.num;
    }

};

struct NoteInfo
{
    double beatOffset;
    double beatDistanceOffset;
    double scroll;
    Note *note;
};


#endif // NOTE_H
