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

        self._testLoop = [
            self.birthYear,
            self.issueYear,
            self.expirationYear,
            self.height,
            self.hairColor,
            self.eyeColor,
            self.PID,
            self.CID
        ]

        self._reqFields = [
            self.birthYear,
            self.issueYear,
            self.expirationYear,
            self.height,
            self.hairColor,
            self.eyeColor,
            self.PID,
            #self.CID
        ]
        return
    
    def isValid(self):
        for f in self._reqFields:
            if(f == None):
                return False
        return True