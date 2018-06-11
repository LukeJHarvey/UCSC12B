//-----------------------------------------------------------------------------
// SimulationStub.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.lang.*;
import java.util.Scanner;

public class Simulation {

//-----------------------------------------------------------------------------
//
// The following function may be of use in assembling the initial backup and/or
// storage queues.  You may use it as is, alter it as you see fit, or delete it
// altogether.
//
//-----------------------------------------------------------------------------

	public static Job getJob(Scanner in) {
		String[] s = in.nextLine().split(" ");
		int a = Integer.parseInt(s[0]);
		int d = Integer.parseInt(s[1]);
		return new Job(a, d);
	}

//-----------------------------------------------------------------------------
//
// The following stub for function main contains a possible algorithm for this
// project.  Follow it if you like.  Note that there are no instructions below
// which mention writing to either of the output files.  You must intersperse
// those commands as necessary.
//
//-----------------------------------------------------------------------------

	public static void main(String[] args) throws IOException {
		String filename = args[0];
		PrintWriter report = new PrintWriter(new FileWriter(args[0]+".rpt"));
		PrintWriter trace = new PrintWriter(new FileWriter(args[0]+".trc"));
		Scanner in = new Scanner(new File(filename));
		String[] N = in.nextLine().split(" ");
		int jobs = Integer.parseInt(N[0]);
		Queue bigBoy = new Queue();
		for(int i = 0; i < jobs; i++) {
			bigBoy.enqueue(getJob(in));
		}
		int curr = 1;
		while(curr < jobs) {
			//Initializes Processors and time
			int time = 0;
			System.out.println("Time: " + time);
			System.out.println("0: " + bigBoy);
			Queue[] processors = new Queue[curr];
			for(int i = 0; i < curr; i++) {
				processors[i] = new Queue();
				System.out.println((i+1) + ": " + processors[i]);
			}

			//Start Jobs
			while(((Job)(bigBoy.peek())).getFinish() == -1) {
				//Check what time is next;
				int temp;
				temp = ((Job)(bigBoy.peek())).getArrival();
				for(int i = 0; i < curr; i++) {
					if(!processors[i].isEmpty()) {
						int x = ((Job)(processors[i].peek())).getArrival();
						temp = x > temp ? x:temp;
					}
				}
				time = temp;

				System.out.println("Time: " + time);
				while(time == ((Job)(bigBoy.peek())).getArrival()) {
					Queue Q = processors[0];

					for(int i = 1; i < curr; i++) {
						if(Q.length() > processors[i].length()) {
							Q = processors[i];
						}
						else if(Q.length() <= processors[i].length()) {
							Q.enqueue(bigBoy.dequeue());
							break;
						}
					}
				}
				
			}
		}
	}
}

