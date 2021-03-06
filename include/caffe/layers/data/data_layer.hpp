#ifndef CAFFE_DATA_LAYERS_HPP_
#define CAFFE_DATA_LAYERS_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>


#include <string>
#include <utility>
#include <vector>

#include "boost/scoped_ptr.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/layers/data/base_data_layer.hpp"
#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/data_transformer.hpp"
#include "caffe/layer.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/db.hpp"

namespace caffe {


template <typename Dtype>
class DataLayer : public BaseDataLayer<Dtype>
{
 public:
  explicit DataLayer(const LayerParameter& param) : BaseDataLayer<Dtype>(param) {}
  virtual ~DataLayer();
  virtual inline const char* type() const { return "Data"; }
  
  virtual void DataLayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
	virtual void InternalThreadEntry(int gpu_id);
 protected:
  

  shared_ptr<db::DB> db_;
  shared_ptr<db::Cursor> cursor_;
 
  
 	vector<cv::Mat> cv_img;
 	Datum* datum;
 	vector<int> rand_length;
 	
 	int sum;
};


}  // namespace caffe

#endif  // CAFFE_BASE_DATA_LAYERS_HPP_
