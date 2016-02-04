package com.me.datastructure; 
  
import java.util.Random; 
import java.util.TreeSet; 
  
public class RainDropExp { 
     static Random rdn = new Random(); 
     public static int rainDrop(){ 
         TreeSet<WetArea> set = new TreeSet<WetArea>(); 
         int i = 0; 
         while(true){ 
             oneDrop(set); 
             i++; 
             if(allWet(set)){ 
                 break; 
             } 
         } 
         return i; 
     } 
     public static void oneDrop(TreeSet<WetArea> set){ 
         double d = rdn.nextDouble(); 
         WetArea drop = new WetArea(d); 
         WetArea higher = set.ceiling(drop); 
          
         if (higher != null && drop.canMerge(higher)){ 
             drop = drop.merge(higher); 
             set.remove(higher); 
         } 
         WetArea lower = set.floor(drop); 
         if(lower != null && drop.canMerge(lower)){ 
             drop = drop.merge(lower); 
             set.remove(lower); 
         } 
         set.add(drop); 
     } 
     public static boolean allWet(TreeSet<WetArea> set){ 
         if(set.isEmpty()){ 
             return false; 
         } l
         if(set.size() == 1){ 
             return set.first().length() == 1.0; 
         } 
         return false; 
     } 
     static class WetArea implements Comparable{ 
         private double left; 
         private double right; 
         public WetArea(double centerPos){ 
             left = Math.max(centerPos - 0.005, 0); 
             right = Math.min(centerPos + 0.005, 1); 
         } 
         public WetArea(double left, double right){ 
             this.left = left; 
             this.right = right; 
         } 
         public double length(){ 
             return right-left; 
         } 
         public double centerPos(){ 
             return (right+left)/2.0; 
         } 
         public WetArea merge(WetArea another){ 
             if (this.left<=another.right && this.right >=  
another.left){ 
                 return new WetArea(Math.min(left,  
another.left), Math.max(right, another.right)); 
             } 
             throw new IllegalArgumentException(); 
         } 
         public boolean canMerge(WetArea another){ 
             return this.left<=another.right && this.right >=  
another.left; 
         } 
         /* (non-Javadoc) 
          * @see  
java.lang.Comparable#compareTo(java.lang.Object) 
          */ 
         @Override 
         public int compareTo(Object o) { 
             if (o instanceof WetArea){ 
                 WetArea o1 = (WetArea)o; 
                 double x = this.centerPos() - o1.centerPos(); 
                 if (x > 0){ 
                     return 1; 
                 }else if (x<0){ 
                     return -1; 
                 }else{ 
                     return 0; 
                 } 
                  
             } 
             throw new ClassCastException(); 
         } 
     } 
     public static void main(String[] args){ 
         int count = 10000; 
         long start = System.currentTimeMillis(); 
         int sum = 0; 
         for (int i=0; i<count; i++){ 
             sum += rainDrop(); 
         } 
         long usetime = (System.currentTimeMillis()-start)/1000; 
         System.out.println("use time=" + usetime + "s"); 
         System.out.println("avg=" + sum/(double)count); 
     } 
} 
