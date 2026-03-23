from sklearn.metrics import normalized_mutual_info_score
#true_labels = [1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3] # True classes
#predicted_clusters = [1,1,1,1,1,2,3,3,1,2,2,2,2,2,3,3,3] # Predicted clusters 
#true_labels = [1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3]
#predicted_clusters = [1,1,1,1,2,2,1,1,1,2,2,2,2,2,2,2,1,1,1,2]
true_labels = [1]*50+[2]*50+[3]*50
predicted_clusters=[1]*50+[2]*98+[3]*2
# NMIを計算
nmi = normalized_mutual_info_score(true_labels, predicted_clusters)
print("NMI:", nmi)