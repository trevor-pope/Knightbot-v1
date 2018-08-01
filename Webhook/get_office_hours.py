office_hours = {

    'kwak':" 2:00 p.m., Monday and Wednesday",
    'bell':" 3 to 4:30 p.m., Monday and Wednesday",
    'garrison':" 5:30 p.m., Monday and Wednesday",
    'brouwer':" 10:00 to 11:00 a.m., Tuesday and Thursday",
    'el jeaid':" 8:30 a.m., Tuesday and Thursday",
    'miller':" 1:00 p.m. Monday and 3:00 p.m. Wednesday"    





    }


def give_office_hours(name):
    print(name)
    hours = office_hours[name[0]]
    msg = name[0] + "'s office hours are at" + hours
    return msg

