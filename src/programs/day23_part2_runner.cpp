#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day23_part2_runner.h"
#include "runner.h"

Day23Part2Runner::Day23Part2Runner(std::string name):Runner(name)
{
    for (int i=0; i<NUM_NICS; i++)
    {
        m_to_nics[i]=NULL;
        m_from_nics[i]=NULL;
    }
    m_nat_x=-1;
    m_nat_y=-1;
    m_nat_prior_sent_y=-1;
}

Day23Part2Runner::~Day23Part2Runner()
{
}

int Day23Part2Runner::run()
{
    long value;
    int rc;
    bool sent_to_nic[NUM_NICS];
    for (int i=0; i<NUM_NICS; i++)
        sent_to_nic[i]=false;
    
    std::cout << "Entering Network Switch Loop" << std::endl;
    
    // poll all the NICs for outputs
    for (int i=0; i<NUM_NICS; i++)
    {
        int rc1, rc2, rc3;
        long dest, x, y;
        while (m_from_nics[i]->hasAvailableElements())
        {
            rc=m_from_nics[i]->getNext(&dest);
            if (rc != SUCCESS)
            {
                std::cerr << "Error retrieving destination value from NIC " << i << std::endl;
                return rc;
            }
            rc=m_from_nics[i]->getNext(&x);
            if (rc != SUCCESS)
            {
                std::cerr << "Error retrieving x value from NIC " << i << std::endl;
                return rc;
            }
            rc=m_from_nics[i]->getNext(&y);
            if (rc != SUCCESS)
            {
                std::cerr << "Error retrieving y value from NIC " << i << std::endl;
                return rc;
            }
            std::cout << "  Network card " << i << " sending message to dest=" << dest << " with values x=" << x << " y=" << y << std::endl;
            if (dest==255)
            {
                std::cout << "  NAT sent from network card " << i << " sending to 255 with x=" << x << "and y=" << y << std::endl;
                m_nat_x=x;
                m_nat_y=y;
            }
            else
            {
                if (dest < 0 || dest >= NUM_NICS)
                {
                    std::cerr << "Invalid destination network address " << dest << " received from NIC " << i << std::endl;
                    return ERR_BAD_NETWORK_ADDRESS;
                }
                m_to_nics[dest]->add(x);
                m_to_nics[dest]->add(y);
                sent_to_nic[i]=true;
            }
        }
    }

    // sent -1 to any NIC that doesn't have data
    bool isIdle=true;
    for (int i=0; i<NUM_NICS; i++)
    {
        if (sent_to_nic[i]==false)
        {
            std::cout << "  Nothing sent to NIC " << i << ".  Sending -1" << std::endl;
            m_to_nics[i]->add(-1);
        }
        else
        {
            isIdle=false;
        }
    }
    
    if (isIdle)
    {
        std::cout << "  Idle condition detected. Sending x=" << m_nat_x << " and y=" << m_nat_y << " from NAT to 0" << std::endl;
        if (m_nat_y==m_nat_prior_sent_y)
        {
            std::cout << "****** This is a duplciate y-value sent from NAT. Got the solution" << std::endl;
            m_terminated=true;
            return SUCCESS;
        }
        m_to_nics[0]->add(m_nat_x);
        m_to_nics[0]->add(m_nat_y);
        m_nat_prior_sent_y=m_nat_y;
    }
    
    return INPUT_WAIT;
}

void Day23Part2Runner::addNic(int number, InputterOutputter * to_nic, InputterOutputter * from_nic)
{
    m_to_nics[number]=to_nic;
    m_from_nics[number]=from_nic;
}

int Day23Part2Runner::getFirstDupeNatY()
{
    return m_nat_prior_sent_y;
}
