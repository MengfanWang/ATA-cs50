import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        # TODO
        self.positives = []
        file = open(positives, "r")
        for line in file:
            if line.startswith(';') == False:
                self.positives.append(line.strip())
        file.close()
        
        self.negatives = []
        file = open(negatives, "r")
        for line in file:
            if line.startswith(';') == False:
                self.negatives.append(line.strip())
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # TODO
        sum = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        for token in tokens:
            if token.lower() in self.positives:
                sum += 1
            elif token.lower() in self.negatives:
                sum -= 1
            else:
                sum = sum
        return sum
