int countOccurence(String entry, char characterToCount){
  String tempString = entry;
  int counter;
  while(tempString.indexOf(characterToCount) > 0){
    counter++;
    tempString = tempString.substring(tempString.indexOf(characterToCount) + 1);
  }

  return counter;
}