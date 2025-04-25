#include <iostream>
#include <fstream>

#include "rtc_base/physical_socket_server.h"
#include "rtc_base/thread.h"
#include "api/scoped_refptr.h"
#include "api/create_peerconnection_factory.h"
#include "api/peer_connection_interface.h"
#include "pc/test/fake_video_track_source.h"

class DummySetSessionDescriptionObserver : public webrtc::SetSessionDescriptionObserver {
public:
    static webrtc::scoped_refptr<DummySetSessionDescriptionObserver> Create() {
        return webrtc::make_ref_counted<DummySetSessionDescriptionObserver>();
    }

    void OnSuccess() override {
        std::cout << "Set session description success." << std::endl;
    }
    void OnFailure(webrtc::RTCError error) override {
        std::cerr << "Set session description failed: " << error.message() << std::endl;
    }
};

class SDPObserver : public webrtc::CreateSessionDescriptionObserver {
public:
    SDPObserver(webrtc::scoped_refptr<webrtc::PeerConnectionInterface> pc) : pc(pc) {}

    void OnSuccess(webrtc::SessionDescriptionInterface* desc) override {
        pc->SetLocalDescription(DummySetSessionDescriptionObserver::Create().get(), desc);
        std::string sdp;
        desc->ToString(&sdp);
        std::cout << "SDP: \n" << sdp << std::endl;

        std::ofstream sdp_file("offer.sdp");
        sdp_file << sdp;
        sdp_file.close();
    }
    void OnFailure(webrtc::RTCError error) override {
        std::cerr << "Failed to create SDP: \n" << error.message() << std::endl;
    }
private:
    webrtc::scoped_refptr<webrtc::PeerConnectionInterface> pc;

};

int main() {
    webrtc::PhysicalSocketServer socket_server;
    webrtc::AutoSocketServerThread main_thread(&socket_server);

    auto factory = webrtc::CreatePeerConnectionFactory(
        &main_thread, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr
    );

    webrtc::PeerConnectionInterface::RTCConfiguration config;
    webrtc::PeerConnectionDependencies dependencies(nullptr);
    auto error_or_peer_connection = factory->CreatePeerConnectionOrError(config, std::move(dependencies));
    webrtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection = nullptr;
    if (error_or_peer_connection.ok())
    {
        peer_connection = error_or_peer_connection.MoveValue();
    }
        
    // auto video_source = webrtc::FakeVideoTrackSource::Create(false);
    // auto video_track = factory->CreateVideoTrack(video_source, "Renderer");

    // auto result_or_error = peer_connection->AddTrack(video_track, {"stream_id"});

    // webrtc::scoped_refptr<SDPObserver> sdp_observer = webrtc::make_ref_counted<SDPObserver>(peer_connection);
    // peer_connection->CreateOffer(sdp_observer.get(), webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());


    // std::cout << "Waiting for SDP..." << std::endl;
    // while (!std::ifstream("offer.sdp").good())
    // {
    //     webrtc::Thread::SleepMs(500);
    // }
    
    // std::ifstream sdp_file("offer.sdp");
    // auto answer_sdp = std::string((std::istreambuf_iterator<char>(sdp_file)), std::istreambuf_iterator<char>());

    // webrtc::SdpParseError error;
    // std::unique_ptr<webrtc::SessionDescriptionInterface> answer_desc = webrtc::CreateSessionDescription(webrtc::SdpType::kAnswer, answer_sdp, &error);
    // peer_connection->SetRemoteDescription(DummySetSessionDescriptionObserver::Create().get(), answer_desc.release());

    // while (true) {
    //     webrtc::Thread::SleepMs(1000);
    // }

    return 0;
}