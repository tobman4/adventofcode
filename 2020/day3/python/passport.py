class passport:
    def __init__(self):
        self.birthYear = None
        self.issueYear = None
        self.expirationYear = None
        self.height = None
        self.hairColor = None
        self.eyeColor = None
        self.PID = None
        self.CID = None

        self.OG = None
        return
    
    def isValid(self):
        """
        good good code
        """

        if(self.birthYear == None): return "Missing birthYear"
        if(self.issueYear == None): return "Missing issueYear"
        if(self.expirationYear == None): return "Missing expirationYear"
        if(self.height == None): return "Missing height"
        if(self.hairColor == None): return "Missing hairColor"
        if(self.eyeColor == None): return "Missing eyeColor"
        if(self.PID == None): return "Missing PID"
        #if(self.CID == None): return "Missing CID"

        return "GOOD"

    def _pythonIsBad(data):
        if(data == None):
            return "Null"
        else:
            return data

    def __str__(self):
        out = "CID = %s\n" % self.CID
        out += "PID = %s\n" % self.PID
        out += "birth year = %s\n" % self.birthYear
        out += "issue year = %s\n" % self.issueYear
        out += "expiration year = %s\n" % self.expirationYear
        out += "height = %s\n" % self.height # <----- fix cm/in
        out += "hair color = %s\n" % self.hairColor
        out += "eye color = %s\n" % self.eyeColor
        return out;