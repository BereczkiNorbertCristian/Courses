/**
 * Created by bnorbert on 21.10.2016.
 */
public class StringNetworkWrapper{

    String insideString;

    StringNetworkWrapper(String stri){
        int n=0;
        char[] chrs=stri.toCharArray();
        for(int i=0;i<stri.length();i++){
            if(chrs[i] == '#'){
                n=i;
                break;
            }
        }
        insideString=stri.substring(0,n);
    }

    String getString(){
        return insideString;
    }

}