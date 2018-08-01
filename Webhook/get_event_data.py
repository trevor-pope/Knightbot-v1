event_data = {
    'graduation':" Tuesday, May 8, 2018, from 9 to 7",
    'knight discovery camp':" Friday, June 28, starting at 11 a.m."
    }


def give_event_data(event):
    msg = event + " is on" + event_data[event]
    return msg

