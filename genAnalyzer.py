from ROOT import TFile, TTree, TH1F, TLorentzVector, TMath, TRandom, TClonesArray, TLegend, TCanvas



f_RH_1           = TFile.Open("one_tev_Z_prime.root", "read")


tree = f_RH_1.Get("LHEF")




def getParticles(tree):
	nParticles = tree.GetLeaf('Particle_size').GetValue()
	Particles=[]
	for j in range(int(nParticles)):
			pt = tree.GetLeaf('Particle.PT').GetValue(j)
			eta = tree.GetLeaf('Particle.Eta').GetValue(j)
			phi= tree.GetLeaf('Particle.Phi').GetValue(j)
			mass = tree.GetLeaf('Particle.M').GetValue(j)
			pid = tree.GetLeaf('Particle.PID').GetValue(j)
			cand={'pt':pt, 'eta':eta, 'phi':phi,'mass':mass,'pid':pid}
			Particles.append(cand)
	return Particles


def setHistoStyle(histogram, color):
    histogram.SetLineColor(color)
    histogram.SetMarkerStyle(8)
    histogram.SetMarkerColor(color)
    histogram.SetMarkerSize(.5)

def draw1D(l_histogram, range,l_legend):
  for TH2FCount, histo in enumerate(l_histogram):
    setHistoStyle(histo, colors[TH2FCount])
    histo.SetStats(0)
    histo.GetYaxis().SetTitleOffset(1.4)
    if TH2FCount == 0: histo.Draw()
    if TH2FCount > 0: histo.Draw("same")
  makeLegend1D(l_legend, l_histogram)

def makeLegend(legend, histogram):
  legend.SetTextSize(0.03)
  legend.SetFillStyle(0)
  legend.SetHeader(histogram[0].GetTitle())
  for TH2FCount, histo in enumerate(histogram):
    legend.AddEntry(histo,fileListName[TH2FCount],"lep")
  legend.Draw()


def makeLegend1D(legend, histogram):
  legend.SetTextSize(0.03)
  legend.SetFillStyle(0)
  for TH2FCount, histo in enumerate(histogram):
    legend.AddEntry(histo,histo.GetName(),"lep")
  legend.Draw()

def drawPlot(l_histogram,trees, l_legend):
	for TH2FCount, histo in enumerate(l_histogram):
	    setHistoStyle(histo, TH2FCount+1)
	    histo.SetStats(0)
	    histo.GetYaxis().SetTitleOffset(1.4)
	    if TH2FCount == 0: histo.Draw()
	    if TH2FCount > 0: histo.Draw("same")
	makeLegend1D(l_legend, l_histogram)


TH1F_b_eta = r.TH1F("TH1F_b_eta", "TH1F_b_eta; #eta", 100, -4, 4)

for count in range(tree.GetEntries()):
	tree.GetEntry(count)
	particles = getParticles(tree)
	for particle in particles:
		print particle['pid']
		#if particle['pid'] == 23:
			#print particle['pt']

		if (particle['pid'])==13:
				mu_pt = particle['pt']
				mu_eta = particle['eta']
				mu_phi = particle['phi']
				mu_mass = particle['mass']
				print "pos"
		
	

		if (particle['pid'])==-13:
				nMu_pt = particle['pt']
				nMu_eta = particle['eta']
				nMu_phi = particle['phi']
				nMu_mass = particle['mass']
				print "neg"

	mu_TL =  TLorentzVector()
	mu_TL.SetPtEtaPhiM(mu_pt,mu_eta,mu_phi,mu_mass)
	nMu_TL =  TLorentzVector()
	nMu_TL.SetPtEtaPhiM(nMu_pt,nMu_eta,nMu_phi,nMu_mass)
	TH1F_b_eta.Fill(nMu_TL.eta())
	TH1F_b_eta.Fill(mu_TL.eta())

	 

	mumu_inv_m = (nMu_TL + mu_TL).M()

	print mumu_inv_m
c1 = TCanvas()

TH1F_b_eta.Draw()
c1.SaveAs("output/TH1F_b_eta")










