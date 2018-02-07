
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef CHAIN_H
#define CHAIN_H

#include <cstdlib>


template <typename T>
class Chain {

    typedef struct Link {
        T _element;
        Link *_previous;
        Link *_next;
    } Link;

    public :
        Chain() : _readBuffer(0), _writeBuffer(0), _nLinks(0) {
        }


        Chain(unsigned int nLinks, const T &element) {
            for(unsigned int iLink = 0; iLink < nLinks; iLink++) {
                this->insert(element);
            }
        }


        ~Chain() {
        }


        bool isEmpty(void) const {
            bool isChainEmpty = false;
            if(this->_nLinks == 0) {
                isChainEmpty = true;
            }
            return isChainEmpty;
        }


        unsigned int size(void) const {
            return this->_nLinks;
        }


        void moveReadBuffer(int nFrames) {
            if(nFrames >= 0) {
                moveForward(this->_readBuffer, (unsigned int)nFrames);
            } else {
                moveBackward(this->_readBuffer, (unsigned int)abs(nFrames));
            }
        }


        void moveWriteBuffer(int nFrames) {
            if(nFrames >= 0) {
                moveForward(this->_writeBuffer, (unsigned int)nFrames);
            } else {
                moveBackward(this->_writeBuffer, (unsigned int)abs(nFrames));
            }
        }


        const T &read(void) {
            return this->_readBuffer->_element;
        }


        void insert(const T& element) {
            Link *newLink = new Link;
            newLink->_element = element;
            this->insert(newLink);
        }


	void replace(const T &element) {
            this->_writeBuffer->_element = element;
        }


        void turn(void) {
            this->_writeBuffer = this->_writeBuffer->_next;
            this->_readBuffer  = this->_readBuffer->_next;
        }

        // erase at read buffer only
        void erase(void) {
            if(this->size() == 1) {
                this->eraseInSingleLinkChain();
            } else {
                this->eraseInMultipleLinksChain();
            }
        }	


    private :
        Link *_readBuffer;
        Link *_writeBuffer;
        unsigned int _nLinks;


        Link *next(Link *buffer) {
            return buffer->_next;
        }

        Link *previous(Link *buffer) {
            return buffer->_previous;
        }	

        void moveForward(Link *buffer, unsigned int nLinks = 1) {
            for(unsigned int iLink = 0; iLink < nLinks; iLink++) {
                buffer = this->next(buffer);
            }
        }


        void moveBackward(Link *buffer, unsigned int nLinks = 1) {
            for(unsigned int iLink = 0; iLink < nLinks; iLink++) {
                buffer = this->previous(buffer);
            }
        }


        void insertInEmptyChain(Link *newLink) {
            newLink->_previous = newLink;
            newLink->_next     = newLink;
            this->_writeBuffer = newLink;
            this->_readBuffer  = newLink;
            this->_nLinks++;
        }


	void insertInNonEmptyChain(Link *newLink) {
            newLink->_next     = this->_writeBuffer;
            newLink->_previous = this->previous(this->_writeBuffer);
            // the order here is critical
            this->_writeBuffer->_previous->_next = newLink;
            this->_writeBuffer->_previous        = newLink;
            this->_nLinks++;
	}


        void insert(Link *newLink) {
            if(this->isEmpty()) {
                this->insertInEmptyChain(newLink);
            } else {
                this->insertInNonEmptyChain(newLink);
            }
        }


        void eraseInMultipleLinksChain(void) {
            if(this->_readBuffer == this->_writeBuffer) {
                this->_writeBuffer = this->moveBackward(this->_writeBuffer);
            }
            Link *newBuffer = this->next(this->_readBuffer);
            this->_readBuffer->_previous->_next = this->next(this->_readBuffer);
            this->_readBuffer->_next->_previous = this->previous(this->_readBuffer);
            delete this->_readBuffer;
            this->_readBuffer = newBuffer;
            this->_nLinks--;
        }


        void eraseInSingleLinkChain(void) {
            if(this->_readBuffer == this->_writeBuffer) {
                this->_writeBuffer = 0;
            }
            delete this->_readBuffer;
            this->_readBuffer = 0;
            this->_nLinks--;
        }

};

#endif
